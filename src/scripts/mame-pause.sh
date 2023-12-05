for  r  in  $( pgrep mame )
   do 
      sudo kill -SIGSTOP $r;
  done 
echo Paused !
