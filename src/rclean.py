# Author: Prathamesh Shivade

import os
import zipfile
import re
import subprocess
import shutil
import time
import datetime
from _winreg import *

print "Extracting and renaming the recorded-game files. Please wait..."

# Find path of SaveGame folder
reg = ConnectRegistry(None, HKEY_LOCAL_MACHINE)
reg_key = OpenKey(reg, r"SOFTWARE\Microsoft\DirectPlay\Applications\Age of Empires II")
savegame_path = EnumValue(reg_key, 4)[1]

if savegame_path[-1] != "\\":
    savegame_path = savegame_path + "\\"

savegame_path = savegame_path + "SaveGame"

os.chdir(savegame_path)

# This file will contain path of download directory
f = open('download_path.txt', 'r')
download_path = f.readline()

# Extract games from archives
for file in os.listdir(download_path):
    if re.match("recording(.)*.zip", file) or re.search(".vs(.)*.zip", file):
        path = download_path + "\\" + file
        zf = zipfile.ZipFile(path, "r")
        zf.extractall(savegame_path)
        zf.close()
        delete_command = "del \"" + path + "\""
        subprocess.call(delete_command, shell=True)

# Rename
for file in os.listdir(savegame_path):
    if re.match("rec*.*.mgz", file) or re.match("partida*.*.mgz", file):
        temp_stamp = file.split('.')[1].split('-')[0]
        my_date = datetime.datetime.strptime(temp_stamp, "%Y%m%d")
        time_stamp = "[" + my_date.strftime("%d-%b-%Y") + "-" + file.split('.')[1].split('-')[1][:-2] + "]"

        os.rename(file, "temp.mgx")

        p = subprocess.Popen(["rclean.exe", "temp.mgx"], stdout=subprocess.PIPE)

        game_info = p.stdout.readlines()
        num_players = len(game_info) - 1
        map_name = game_info[0]
        del game_info[0]
        game_info = sorted(game_info)

        players = []
        players.append(game_info[0].split(' ', 1)[1][:-2])
        team = int(game_info[0].split(' ')[0][:1])

        for j in range(1, num_players):
            i = game_info[j]
            next_team = i.split(' ')[0][:1]

            if (int(next_team) == team) & (num_players != 2):
                players.append("+")
            else:
                players.append(" vs ")
                team = int(next_team)
            players.append(i.split(' ', 1)[1][:-2])
        player_string = ''.join(players)
        new_name = player_string + "[" + map_name[:-2] + "]" + time_stamp + ".mgz"
        try:
            os.rename("temp.mgx", new_name)
        except WindowsError:
            os.remove("temp.mgx")

subprocess.call(['explorer', savegame_path])
