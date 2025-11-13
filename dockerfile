#Set up packages in ubuntu
FROM ubuntu:latest
    RUN apt-get update && apt-get install -y build-essential
    RUN gcc --version