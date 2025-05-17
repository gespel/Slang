FROM gespel/debian-base:latest

COPY . .

RUN mkdir build && cd build && cmake .. && make && cd .. && make

ENTRYPOINT ["./slang example/test1.slang"]
