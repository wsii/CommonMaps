// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonMaps.h"
#include "CommonMapsSet.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName CommonMapsTabName("CommonMaps");

#define LOCTEXT_NAMESPACE "FCommonMapsModule"

static void OpenCommonMap_Clicked(const FString MapPath)
{
	if (ensure(MapPath.Len()))
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(MapPath);
	}
}

static bool HasPlayWorld()
{
	return GEditor->PlayWorld != nullptr;
}

static bool HasNoPlayWorld()
{
	return !HasPlayWorld();
}

static bool CanShowCommonMaps()
{
	return HasNoPlayWorld() && !GetDefault<UCommonMapsSet>()->CommonEditorMaps.IsEmpty();
}


static TSharedRef<SWidget> GetCommonMapsDropdown()
{
	FMenuBuilder MenuBuilder(true, nullptr);
	
	for (const FSoftObjectPath& Path : GetDefault<UCommonMapsSet>()->CommonEditorMaps)
	{
		if (!Path.IsValid())
		{
			continue;
		}
		
		const FText DisplayName = FText::FromString(Path.GetAssetName());
		MenuBuilder.AddMenuEntry(
			DisplayName,
			LOCTEXT("CommonPathDescription", "Opens this map in the editor"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateStatic(&OpenCommonMap_Clicked, Path.ToString()),
				FCanExecuteAction::CreateStatic(&HasNoPlayWorld),
				FIsActionChecked(),
				FIsActionButtonVisible::CreateStatic(&HasNoPlayWorld)
			)
		);
	}

	return MenuBuilder.MakeWidget();
}


static void RegisterGameEditorMenus()
{
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	FToolMenuSection& Section = Menu->AddSection("PlayGameExtensions", TAttribute<FText>(), FToolMenuInsert("Play", EToolMenuInsertType::After));
	
	
	FToolMenuEntry CommonMapEntry = FToolMenuEntry::InitComboButton(
		"CommonMapOptions",
		FUIAction(
			FExecuteAction(),
			FCanExecuteAction::CreateStatic(&HasNoPlayWorld),
			FIsActionChecked(),
			FIsActionButtonVisible::CreateStatic(&CanShowCommonMaps)),
		FOnGetContent::CreateStatic(&GetCommonMapsDropdown),
		LOCTEXT("CommonMaps_Label", "Common Maps"),
		LOCTEXT("CommonMaps_ToolTip", "Some commonly desired maps while using the editor"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Level")
	);
	CommonMapEntry.StyleNameOverride = "CalloutToolbar";
	Section.AddEntry(CommonMapEntry);
}



void FCommonMapsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	

	
	if (!IsRunningGame())
	{
		
		if (FSlateApplication::IsInitialized())
		{
			UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateStatic(&RegisterGameEditorMenus));
		}

	}

}

void FCommonMapsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);
	
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCommonMapsModule, CommonMaps);