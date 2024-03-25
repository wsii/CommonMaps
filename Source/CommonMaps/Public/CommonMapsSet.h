// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "UObject/PrimaryAssetId.h"
#include "UObject/SoftObjectPath.h"
#include "CommonMapsSet.generated.h"

/**
 * 
 */
UCLASS(config=EditorPerProjectUserSettings,MinimalAPI)
class UCommonMapsSet : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()
public:
	UCommonMapsSet();
	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface
	
public:
// #if WITH_EDITORONLY_DATA
	/** A list of common maps that will be accessible via the editor detoolbar */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category=Maps, meta=(AllowedClasses="/Script/Engine.World"))
	TArray<FSoftObjectPath> CommonEditorMaps;
// #endif
};
