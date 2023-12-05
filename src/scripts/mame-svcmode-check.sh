#!/bin/bash


function cleanup {
  # Deactivate GPIO pin
  echo $GPIOPIN >/sys/class/gpio/unexport 2>/dev/null
  exit 0
  }

# Clean up when exit
trap cleanup SIGHUP
trap cleanup SIGQUIT
trap cleanup SIGINT
trap cleanup SIGTERM

GPIOPIN=18   # We use GPIO 18 (pin #12)
BOOTSOUND=/home/pi/splash/boot.wav
SVCMSOUND=/home/pi/splash/service-mode.wav
TIMEOUT=5

raspi-gpio set $GPIOPIN pu      # Enable the internal pull-up resistor for this GPIO pin
aplay -q $BOOTSOUND &	  	# Play Boot sound

# Initialize GPIO pin
[ -d /sys/class/gpio/gpio${GPIOPIN} ] && echo $GPIOPIN > /sys/class/gpio/unexport  # Deactivate GPIO pin
echo $GPIOPIN > /sys/class/gpio/export    # Activate GPIO pin
sleep 0.1                                 # A small delay is required so that the system has time
                                          # to properly create and set the file's permission
echo in > /sys/class/gpio/gpio${GPIOPIN}/direction # Input signal
echo both > /sys/class/gpio/gpio${GPIOPIN}/edge    # We use the interrupt controller to avoid a CPU spin loop

read SIGNAL < /sys/class/gpio/gpio${GPIOPIN}/value
if [ $SIGNAL -eq 1 ]; then	# Button not pressed
  inotifywait -q -t $TIMEOUT -e modify /sys/class/gpio/gpio${GPIOPIN}/value > /dev/null
  if [ $? -eq 0 ]; then	# Value has changed
    read SIGNAL < /sys/class/gpio/gpio${GPIOPIN}/value
  fi
fi

if [ $SIGNAL -eq 0 ]; then    # 1=Open/Arcade Mode, 0=Closed/Service Mode
  aplay -q $SVCMSOUND			# Service Mode
  touch /tmp/service-mode.flag		# Activate the flag
fi

