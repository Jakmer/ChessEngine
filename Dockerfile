FROM ubuntu:latest

RUN apt-get update &&  apt-get upgrade -y && apt-get install -y \
	cmake \
	git	\
	build-essential \
	libboost-all-dev

# Install googletest
WORKDIR /usr/src/googletest
RUN git clone https://github.com/google/googletest.git . \
	&& cmake . \
	&& make \
	&& make install

# Install spdlog
WORKDIR /usr/src/spdlog
RUN git clone https://github.com/gabime/spdlog.git . \
	&& cmake . \
	&& make -j$(nproc) \
	&& make install

# Install ChessEngine
WORKDIR /usr/src/app
COPY . .
RUN cmake . \
	&& make \
	&& make install

# Set the runtime library path
ENV LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

COPY scripts/start-client-server.sh /usr/src/app/scripts/start-client-server.sh

RUN chmod +x /usr/src/app/scripts/start-client-server.sh

CMD ["/usr/src/app/scripts/start-client-server.sh"]
