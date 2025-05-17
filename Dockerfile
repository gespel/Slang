FROM gespel/debian-base:latest

COPY . .

RUN mkdir build && cd build && cmake .. && cd .. && make

ENTRYPOINT ["./slang example/test1.slang"]
