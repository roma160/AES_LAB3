FROM ubuntu:latest

RUN apt-get update && apt-get install -y g++ cmake make
RUN apt-get install -y libncurses5-dev libncursesw5-dev

COPY . /usr/src/LAB3
WORKDIR /usr/src/LAB3

RUN cmake -S . -B ./build
RUN cmake --build ./build

CMD ./build/main