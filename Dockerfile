FROM gcc:latest

RUN apt-get update && apt-get install -y cmake git

WORKDIR /usr/src/googletest
RUN git clone https://github.com/google/googletest.git . \
	&& cmake . \
	&& make \
	&& make install

WORKDIR /usr/src/app
COPY . .
RUN cmake . \
	&& make \
	&& make install

WORKDIR /usr/src/app/tests/EngineStarterTest
RUN cmake . \
	&& make \
    && make install \
	&& ./EngineStarterTest

CMD ["EngineStarter"]