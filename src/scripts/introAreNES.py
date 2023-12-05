import vlc
import time

splash = '/home/pi/splash/'


def create_media():
    video = vlc.Media(splash+"intro.mp4")
    return video


# end def


def play_video(player, video):
    # Load the media into the player
    player.set_media(video)

    player.audio_set_volume(100)

    # Play the video
    player.play()
    time.sleep(10)


def main():
    # Create the player
    player = vlc.MediaPlayer()
    player.set_fullscreen(False)

    # Create the media objects
    video = create_media()

    # Play video
    play_video(player, video)



# end def


if __name__ == '__main__':
    main()

