FROM fedora:latest

RUN dnf -y install cmake make automake gcc gcc-c++ kernel-devel
COPY . .
RUN mkdir build && cd build && cmake .. -DSLANG_DEBUG=ON && make && cd .. && make
RUN chmod +x test.sh

ENTRYPOINT ["./test.sh"]
