// Copyright 2023 Betide Studio. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "VoiceChat.h"
#include "EIK_Voice_Subsystem.generated.h"

UENUM(BlueprintType)
enum class EEVIKResultCodes :uint8
{
	Success = 0,
	Failed = 1
};

struct FEVIKChannelCredentials : public FJsonSerializable
{
	FString OverrideUserId;
	FString ClientBaseUrl;
	FString ParticipantToken;

	BEGIN_JSON_SERIALIZER
		JSON_SERIALIZE("override_userid", OverrideUserId);
	JSON_SERIALIZE("client_base_url", ClientBaseUrl);
	JSON_SERIALIZE("participant_token", ParticipantToken);
	END_JSON_SERIALIZER
};

USTRUCT(BlueprintType)
struct FDeviceEVIKSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="EVIK")
	FString ID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="EVIK")
	FString DisplayName;
	
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FEIKResultDelegate, bool, bWasSuccess, EEVIKResultCodes, Result);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FEIKRoomTokenResultDelegate, bool, bWasSuccess, FString, RoomData);

/**
 * 
 */
UCLASS()
class EOSVOICEINTEGRATIONKIT_API UEIK_Voice_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(Category="EVIK")
	bool EVIK_Local_Initialize();
	
	IVoiceChat* EVIK_Local_GetVoiceChat();

	UFUNCTION(Category="EVIK")
	void EVIK_Local_Connect(const FEIKResultDelegate& ResultDelegate);
	
	IVoiceChat* EVIK_VoiceChat;
};
