FROM ubuntu:latest

RUN apt-get update &&  apt-get upgrade -y && apt-get install -y \
	cmake \
	git \
	build-essential \
	libboost-all-dev \
	ccache \
	ninja-build \
    gdb \
    expect 

# Install googletest
WORKDIR /usr/src/googletest
RUN git clone https://github.com/google/googletest.git . \
    && cmake -G Ninja . \
    && ninja -j4 \
    && ninja install

# Install spdlog
WORKDIR /usr/src/spdlog
RUN git clone https://github.com/gabime/spdlog.git . \
    && cmake -G Ninja . \
    && ninja -j4 \
    && ninja install

# Install ChessEngine
WORKDIR /usr/src/app
COPY . .
RUN cmake -G Ninja -DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache . \
    && ninja -j4 \
    && ninja install

# Set the runtime library path
ENV LD_LIBRARY_PATH=/usr/local/lib

COPY scripts/start-client-server.sh /usr/src/app/scripts/start-client-server.sh

RUN chmod +x /usr/src/app/scripts/start-client-server.sh

CMD ["/usr/src/app/scripts/start-client-server.sh"]
