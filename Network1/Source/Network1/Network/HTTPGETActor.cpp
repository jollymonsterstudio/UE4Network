// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPGETActor.h"

#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Network1/Network1Character.h"
#include "Network1/UI/HTTPResponseWidget.h"

// Sets default values
AHTTPGETActor::AHTTPGETActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Area"));
	SetRootComponent(OverlapComponent);

	ResponseWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Response Widget"));
	ResponseWidgetComponent->SetupAttachment(OverlapComponent);
	
	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AHTTPGETActor::BeginPlay()
{
	Super::BeginPlay();

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

// Called every frame
void AHTTPGETActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ResponseWidgetComponent)
	{
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		if(CameraManager)
		{
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraManager->GetCameraLocation(), ResponseWidgetComponent->GetComponentLocation());
			LookAtRotation.Pitch = 0.f;
			LookAtRotation.Roll = 0.f;
			LookAtRotation.Yaw -= 180.f;
			ResponseWidgetComponent->SetWorldRotation(LookAtRotation);
		}
	}
}

void AHTTPGETActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ResponseWidgetComponent)
	{
		UHTTPResponseWidget* ResponseWidget = Cast<UHTTPResponseWidget>(ResponseWidgetComponent->GetWidget());
		if(ResponseWidget)
		{
			ResponseWidget->ShowLoading(true);

			FString Username;
			ANetwork1Character* Character = Cast<ANetwork1Character>(OtherActor);
			if(Character && !Character->GetUsername().IsEmpty())
			{
				Username = Character->GetUsername();
			}

			SendHTTPGet(Username);
		}
	}
}

void AHTTPGETActor::SendHTTPGet(FString Username)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	if(Username.IsEmpty())
	{
		Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnGetUsersResponse);
		Request->SetURL("http://localhost:8080/jms-api/users");
	}
	else
	{
		Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnGetUserByUsernameResponse);
		Request->SetURL(FString::Printf(TEXT("http://localhost:8080/jms-api/user/%s"), *Username));
	}

	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}

void AHTTPGETActor::OnGetUsersResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;

	if(ResponseWidgetComponent)
	{
		UHTTPResponseWidget* ResponseWidget = Cast<UHTTPResponseWidget>(ResponseWidgetComponent->GetWidget());
		if(ResponseWidget)
		{
			ResponseWidget->ShowLoading(false);

			if(Response->GetResponseCode() == 200)
			{
				const FString ResponseBody = Response->GetContentAsString();

				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

				if(FJsonSerializer::Deserialize(Reader, JsonObject))
				{
					TArray<TSharedPtr<FJsonValue>> UserArray = JsonObject->GetArrayField("users");

					for(const TSharedPtr<FJsonValue> UserValue : UserArray)
					{
						AddUserToWidget(UserValue->AsObject());
					}
				}
			}
			else
			{
				// TODO: trigger error
				ResponseWidget->ShowError(Response->GetResponseCode(), "Error occured");
			}
		}
	}
}


void AHTTPGETActor::OnGetUserByUsernameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;

	if(ResponseWidgetComponent)
	{
		UHTTPResponseWidget* ResponseWidget = Cast<UHTTPResponseWidget>(ResponseWidgetComponent->GetWidget());
		if(ResponseWidget)
		{
			ResponseWidget->ShowLoading(false);

			if(Response->GetResponseCode() == 200)
			{
				const FString ResponseBody = Response->GetContentAsString();

				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

				if(FJsonSerializer::Deserialize(Reader, JsonObject))
				{
					AddUserToWidget(JsonObject);
				}
			}
			else
			{
				// TODO: trigger error
				ResponseWidget->ShowError(Response->GetResponseCode(), "Error occured");
			}
		}
	}
}

void AHTTPGETActor::AddUserToWidget(TSharedPtr<FJsonObject> JsonObject)
{
	const int32 UserId = JsonObject->GetIntegerField("id");
	const FString Username = JsonObject->GetStringField("username");

	UHTTPResponseWidget* ResponseWidget = Cast<UHTTPResponseWidget>(ResponseWidgetComponent->GetWidget());
	if(ResponseWidget)
	{
		ResponseWidget->AddUser(UserId, Username);
	}
}



