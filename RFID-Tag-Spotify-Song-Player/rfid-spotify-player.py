# Code by Wian Joubert

import serial
import webbrowser
import time
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials

# Set up authentication
sp = spotipy.Spotify(auth_manager=SpotifyClientCredentials(
    # get yours here https://developer.spotify.com/
    client_id='YOUR-CLIENT-ID-HERE',
    client_secret='YOUR-CLIENT-SECRET-HERE'
))

# Some Init and Globals
ser = serial.Serial('COM3', 9600)   # Port & Baud Rate (Match with Arduino Baud)
last_tagID = 0                     # To stop duplicate reads
current_tagID = 0                  
print("=== Awaiting Tag ===\n")

# Correlates read RFID with a Song Name
def handle_new_tagID(tagID):
    print("\n---")
    # Edit as necessary to correlate the two
    tag_song = {
        # Tag ID  :  Song Name
        "0009659B": "Teardrops Bring Me The Horizon",
        "000782FA": "The Summoning Sleep Token",
        "00085B31": "Better Days Currents",
        "000995D2": "Crime And Punishment Ado",
        "00C001E2": "Glimps ERRA"
    }.get(tagID, "Unknown Tag")
    return tag_song

# Just a timer
def countdown():
    print("Redirecting in 5 seconds!")
    for i in range(5, 0, -1):
        print(str(i) + "...")
        time.sleep(1)

# Contacts Spotify API    
def search_for_song(tag_song):
    results = sp.search(q='track:' + tag_song, type='track', limit=1)
    # Print the search results
    if results['tracks']['items']:
        track = results['tracks']['items'][0]
        track_name = track['name']
        track_uri = track['uri']
        track_url = track['external_urls']['spotify']
        duration_ms = track['duration_ms']
        
        # Convert duration from ms to minutes and seconds
        duration_min = duration_ms // 60000
        duration_sec = (duration_ms % 60000) // 1000
        duration = f"{duration_min}:{duration_sec:02}"  # Format duration as "minutes:seconds"
        
        artists = [artist['name'] for artist in track['artists']]
        
        # Create a formatted string for the output
        output = f"""
        | New Tag Detected |
        |---------------|---------------------------------------------------------|
        | Track Name    | {track_name:<30}                          |
        | Artists       | {', '.join(artists):<30}                          |
        | Duration      | {duration:<5} min                                               |
        | Track URI     | {track_uri:<30}                    |
        | Track URL     | {track_url:<30}   |
        |---------------|---------------------------------------------------------|
        """
        print(output)
        countdown()
        webbrowser.open(track_url)
    else:
        print(f"\nNo track found for {tag_song}.\n")

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        if line.startswith("Tag ID: "):
            tagID_str = line.split(": ")[1]
            current_tagID = tagID_str
            if current_tagID != last_tagID:
                last_tagID = current_tagID
                search_for_song(handle_new_tagID(current_tagID))
