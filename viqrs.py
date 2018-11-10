#!/usr/bin/env python
# -*- coding: utf-8 -*-
#Ver 1.0.0

"""Simple Bot to reply to Telegram messages.

This program is dedicated to the public domain under the CC0 license.

This Bot uses the Updater class to handle the bot.

First, a few handler functions are defined. Then, those functions are passed to
the Dispatcher and registered at their respective places.
Then, the bot is started and runs until we press Ctrl-C on the command line.

Usage:
Basic Echobot example, repeats messages.
Press Ctrl-C on the command line or send a signal to the process to stop the
bot.
"""

from telegram.ext import Updater, CommandHandler, MessageHandler, Filters
from subprocess import call
from os import listdir, mkdir, system
import logging


# Enable logging
logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
                    level=logging.INFO)

logger = logging.getLogger(__name__)

def number(code):
    #return int(code.split("?")[1].split("A")[0]
    num = code.split("?")[1].split("A")[0]
    return int(num)

# Define a few command handlers. These usually take the two arguments bot and
# update. Error handlers also receive the raised TelegramError object in error.
def start(bot, update):
    """Send a message when the command /start is issued."""
    update.message.reply_text("Hi! I'm ViQRs. I'm ready to generate your codes. Check /help for information about what I can do.")
    user_id = update.message.from_user.id
    data_dir = "data/" + str(user_id)

    # TODO: check if dir already exist
    mkdir(data_dir)

def help(bot, update):
    """Send a message when the command /help is issued."""
    update.message.reply_text('/code [original_code] [mode] [number]')
    update.message.reply_text('[original_code]: ClubVips?[12_digit_number]A')
    update.message.reply_text('[mode]: -p: for generating previos codes and -n for generating next codes')
    update.message.reply_text('[number]: 1-10')

def code(bot, update):
    """Sends generated codes."""
    command = update.message.text.split()

    # checks if the number of arguments is correct
    if len(command) != 4:
        update.message.reply_text('Error in arguments. Check /help for more information')
        return

    ori_code = update.message.text.split()[1]
    mode = update.message.text.split()[2]
    num = update.message.text.split()[3]

    # checks correction of the arguments
    
    # original code
    ini = "ClubVipsApp?"
    end = "A"
    
    if(ini != ori_code[:len(ini)] or 
       end != ori_code[len(ori_code) - 1] or
       len(ori_code[len(ini):len(ori_code) - 1]) != 12):

       print ori_code[:len(ini)]
       print ori_code[len(ori_code) - 1]
       print ori_code[len(ini):len(ori_code) - 1]
       
       update.message.reply_text("Error in the format of the original code. Check /help for more information")
       return 

    # mode
    if (mode != "-n" and mode != "-p"):
        print mode
        update.message.reply_text("Error in the format of the mode. Check /help for more information")
        return 

    # number
    if int(num) > 10:
        update.message.reply_text("I'm sorry, " + update.message.from_user.first_name + ". I'm afraid I can't let you do that.")
        update.message.reply_text("Request ten codes or less.")


    user_id = update.message.from_user.id
    data_dir = "data/" + str(user_id) + "/"
    data_files = data_dir + "/*"
    system("./bin/viqrs " + ori_code + " " + mode + " " + num + " " + data_dir)
    files = listdir(data_dir)
    files.sort(key=number)
    
    for f in files:
        update.message.reply_text(f)
        bot.send_photo(chat_id=update.message.chat.id, photo=open(data_dir + f, 'rb'))
 
    system("rm -f " + data_files)
             
    return

def error(bot, update, error):
    """Log Errors caused by Updates."""
    logger.warning('Update "%s" caused error "%s"', update, error)


def main():
    """Start the bot."""
    # Create the EventHandler and pass it your bot's token.
    updater = Updater("744312405:AAG7Fae_B5CYfMae5U8OxElS__iRXDY72fg")

    # Get the dispatcher to register handlers
    dp = updater.dispatcher

    # on different commands - answer in Telegram
    dp.add_handler(CommandHandler("start", start))
    dp.add_handler(CommandHandler("help", help))
    dp.add_handler(CommandHandler("code", code))

    # log all errors
    dp.add_error_handler(error)

    # Start the Bot
    updater.start_polling()

    # Run the bot until you press Ctrl-C or the process receives SIGINT,
    # SIGTERM or SIGABRT. This should be used most of the time, since
    # start_polling() is non-blocking and will stop the bot gracefully.
    updater.idle()


if __name__ == '__main__':
    main()
