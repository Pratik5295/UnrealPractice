// Fill out your copyright notice in the Description page of Project Settings.


#include "FDialogueNode.h"

FDialogueNode::FDialogueNode()
{
}

FDialogueNode::~FDialogueNode()
{
}

FDialogueNode::FDialogueNode(FString _SpeakerName, FString _Message)
{
	SpeakerName = _SpeakerName;
	Message = _Message;

	//By default set it to normal
	MessageType = EMessageType::NORMAL;

	Options = TArray<FDialogueOption>();
}
