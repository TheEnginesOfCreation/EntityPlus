// Copyright (C) 1999-2000 Id Software, Inc.
//

/*****************************************************************************
 * name:		ai_chat.h
 *
 * desc:		Quake3 bot AI
 *
 * $Archive: /source/code/botai/ai_chat.c $
 *
 *****************************************************************************/

// time the selected chat takes to type in
float BotChatTime(bot_state_t *bs);
// returns true if the bot can chat at the current position
int BotValidChatPosition(bot_state_t *bs);
// test the initial bot chats
void BotChatTest(bot_state_t *bs);

