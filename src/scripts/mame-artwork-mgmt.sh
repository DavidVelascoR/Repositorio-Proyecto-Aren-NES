#!/bin/bash


inotifywait -m /home/pi/.mame/roms -e create -e moved_to -e delete -e moved_from |
  while read dir action file; do
      case ${action,,} in
          create | moved_to)
              /home/pi/scripts/mame-scraper.sh ${file%.zip}
              ;;
          delete | moved_from)
              /home/pi/scripts/mame-delartwork.sh ${file%.zip}
              ;;
      esac
  done
