// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_HUD.h"

void AFPS_HUD::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to player character
	Character = Cast<AFPS_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AFPS_HUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrosshairTexture && HeartTexture)
	{
		// Find center of canvas
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		// Offset by half of the texture's dimensions to align in center
		FVector2D CrosshairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

		// Heart draw positions
		FVector2D HeartDrawPosition1(20, 20);
		FVector2D HeartDrawPosition2(40, 20);
		FVector2D HeartDrawPosition3(60, 20);
		
		// Gem draw positions
		FVector2D GemDrawPosition(20, 40);

		// Draw the crosshairs at centerpoint
		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);

		// Draw the hearts in the top left corner
		if (Character->Health == 3)
		{
			FCanvasTileItem HeartItem1(HeartDrawPosition1, HeartTexture->Resource, FLinearColor::White);
			HeartItem1.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(HeartItem1);

			FCanvasTileItem HeartItem2(HeartDrawPosition2, HeartTexture->Resource, FLinearColor::White);
			HeartItem2.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(HeartItem2);

			FCanvasTileItem HeartItem3(HeartDrawPosition3, HeartTexture->Resource, FLinearColor::White);
			HeartItem3.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(HeartItem3);
		}
		else if (Character->Health == 2)
		{
			FCanvasTileItem HeartItem1(HeartDrawPosition1, HeartTexture->Resource, FLinearColor::White);
			HeartItem1.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(HeartItem1);

			FCanvasTileItem HeartItem2(HeartDrawPosition2, HeartTexture->Resource, FLinearColor::White);
			HeartItem2.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(HeartItem2);
		}
		else if (Character->Health == 1)
		{
			FCanvasTileItem HeartItem1(HeartDrawPosition1, HeartTexture->Resource, FLinearColor::White);
			HeartItem1.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(HeartItem1);
		}

		// Draw gems at bottom left
		if (Character->Gems >= 1)
		{
			FCanvasTileItem GemItem(GemDrawPosition, GemFullTexture->Resource, FLinearColor::White);
			GemItem.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(GemItem);
		}
		else
		{
			FCanvasTileItem GemItem(GemDrawPosition, GemTexture->Resource, FLinearColor::White);
			GemItem.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(GemItem);
		}
	}
}

