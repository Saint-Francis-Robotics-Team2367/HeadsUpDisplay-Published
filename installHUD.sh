#!/bin/bash
echo Beginning Installation...

/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

brew tap homebrew/science
brew install opencv3

git clone --single-branch --branch ImplementedHUD https://github.com/Saint-Francis-Robotics-Team2367/HeadsUpDisplay-Published.git

echo Installation Complete \o/
