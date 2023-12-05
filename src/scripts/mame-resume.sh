for  r  in  $( pgrep mame )
   do 
      sudo kill -SIGCONT $r;
  done 
/home/pi/scripts/mame-romlist.sh
echo Resumed !
