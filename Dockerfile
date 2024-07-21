FROM gcc:latest

RUN apt-get update && apt-get install -y cmake git

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

# Install EngineStarterTest
WORKDIR /usr/src/app/tests/EngineStarterTest
RUN cmake . \
	&& make \
    && make install 

CMD ["EngineStarter"]