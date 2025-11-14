#Set up packages in ubuntu environment
FROM ubuntu:latest
    RUN sudo apt-get update && sudo apt-get install -y build-essential
    RUN sudo apt-get update && sudo apt-get -qq -y install curl
    RUN sudo apt-get update && sudo apt-get install libsdl2-2.0-0
    RUN sudo apt-get update && sudo apt-get install libsdl2-dev
    RUN gcc --version