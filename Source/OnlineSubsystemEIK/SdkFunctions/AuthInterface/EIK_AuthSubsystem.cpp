﻿// Copyright (c) 2023 Betide Studio. All Rights Reserved.


#include "EIK_AuthSubsystem.h"

#include "OnlineSubsystemEOS.h"
#include "OnlineSubsystemEIK/SdkFunctions/ConnectInterface/EIK_ConnectSubsystem.h"

FEIK_NotificationId UEIK_AuthSubsystem::EIK_Auth_AddNotifyLoginStatusChanged(
	const FEIK_Auth_OnLoginStatusChangedCallback& Callback)
{
	if(	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get("EIK"))
	{
		if (FOnlineSubsystemEOS* EOSRef = static_cast<FOnlineSubsystemEOS*>(OnlineSub))
		{
			EOS_Auth_AddNotifyLoginStatusChangedOptions Options = {};
			Options.ApiVersion = EOS_AUTH_ADDNOTIFYLOGINSTATUSCHANGED_API_LATEST;
			auto Return = EOS_Auth_AddNotifyLoginStatusChanged(EOSRef->AuthHandle, &Options, this, [](const EOS_Auth_LoginStatusChangedCallbackInfo* Data)
			{
				UEIK_AuthSubsystem* Subsystem = static_cast<UEIK_AuthSubsystem*>(Data->ClientData);
				if (Subsystem)
				{
					Subsystem->OnLoginStatusChanged.ExecuteIfBound(Data->LocalUserId, static_cast<EIK_ELoginStatus>(Data->PrevStatus), static_cast<EIK_ELoginStatus>(Data->CurrentStatus));
				}
			});
			return Return;
		}
	}
	UE_LOG(LogEIK, Error, TEXT("Failed to get EOS subsystem"));
	return FEIK_NotificationId();
}

TEnumAsByte<EEIK_Result> UEIK_AuthSubsystem::EIK_Auth_CopyIdToken(const FEIK_EpicAccountId& AccountId,
	FEIK_Auth_IdToken& OutToken)
{
	if(	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get("EIK"))
	{
		if (FOnlineSubsystemEOS* EOSRef = static_cast<FOnlineSubsystemEOS*>(OnlineSub))
		{
			EOS_Auth_CopyIdTokenOptions Options = {};
			Options.ApiVersion = EOS_AUTH_COPYIDTOKEN_API_LATEST;
			Options.AccountId = AccountId.EpicAccountIdBasic;
			EOS_Auth_IdToken* Token = nullptr;
			auto Return = EOS_Auth_CopyIdToken(EOSRef->AuthHandle, &Options, &Token);
			if (Return == EOS_EResult::EOS_Success)
			{
				OutToken = *Token;
			}
			return static_cast<EEIK_Result>(Return);
		}
	}
	UE_LOG(LogEIK, Error, TEXT("Failed to get EOS subsystem"));
	return EEIK_Result::EOS_NotFound;
}

TEnumAsByte<EEIK_Result> UEIK_AuthSubsystem::EIK_Auth_CopyUserAuthToken(const FEIK_EpicAccountId& LocalUserId,
	FEIK_Auth_Token& OutToken)
{
	if(	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get("EIK"))
	{
		if (FOnlineSubsystemEOS* EOSRef = static_cast<FOnlineSubsystemEOS*>(OnlineSub))
		{
			EOS_Auth_CopyUserAuthTokenOptions Options = {};
			Options.ApiVersion = EOS_AUTH_COPYUSERAUTHTOKEN_API_LATEST;
			EOS_Auth_Token* Token = nullptr;
			auto Return = EOS_Auth_CopyUserAuthToken(EOSRef->AuthHandle, &Options, LocalUserId.EpicAccountIdBasic, &Token);
			if (Return == EOS_EResult::EOS_Success)
			{
				OutToken = *Token;
			}
			return static_cast<EEIK_Result>(Return);
		}
	}
	UE_LOG(LogEIK, Error, TEXT("Failed to get EOS subsystem"));
	return EEIK_Result::EOS_NotFound;
}
