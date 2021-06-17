// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to game!"));
    PrintLine(TEXT("Enter text: "));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("Word");
    GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, Input);
}