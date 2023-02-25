/**
 * @file data_section_main.h
 * @author your name (you@domain.com)
 * @brief Gestion du stockage des messages. 
 * @version 0.1
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef DATA_SECTION_MAIN_H
#define DATA_SECTION_MAIN_H

#include <stdbool.h>
#include <wchar.h>
#include <Common.h>

/**
 * @brief Add a message to the server.
 * 
 * @param zFromUser The sender user.
 * @param zToUser The destination user.
 * @param zMsg The message.
 * @param pMsgId The returned id after adding the messsage to the server.
 * @retval EOC_OK Message successfully added.
 */
EOC add_msg(const wchar_t* zFromUser, const wchar_t* zToUser, const wchar_t* zMsg, int* pMsgId);

/**
 * @brief Delete a message from the server.
 * 
 * @param nMsgId 
 * @return EOC 
 */
EOC del_msg(const int nMsgId);

/**
 * @brief Get the msg object
 * 
 * @param nMsgId The message Id.
 * @retval EOC_OK Message successfully found. 
 */
EOC get_msg(const int nMsgId);

/**
 * @brief Retrives the last messages sent from zUser.
 * 
 * @param zUser The source user
 * @param pzMsg Allocated array to contain messages, pzMsg must be sized according to nMsgMaxCount
 * @param nMsgMaxCount The max number of message you can retrive
 * @param pMsgCount The number of retrieved messages
 * 
 * @retval EOC_OK Message successfully found.
 */
EOC get_msg_from(const wchar_t* zUser,const wchar_t** pzMsg, const int nMsgMaxCount, int* pMsgCount);

#endif // DATA_SECTION_MAIN_H