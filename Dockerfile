FROM gespel/debian-base:latest

COPY . .

RUN mkdir build && cd build && cmake .. && make && cd .. && make
RUN chmod +x test.sh

ENTRYPOINT ["./test.sh"]
