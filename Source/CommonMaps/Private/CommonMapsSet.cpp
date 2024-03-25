// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonMapsSet.h"
#include "Misc/App.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(CommonMapsSet)
UCommonMapsSet::UCommonMapsSet()

{
}

FName UCommonMapsSet::GetCategoryName() const
{
	return FApp::GetProjectName();
}

