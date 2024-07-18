# ChessEngine

This is a Chess Engine Project

## Getting Started

Build image

    sudo docker build -t my_chess_engine .

Create container

    sudo docker run --name chess_engine_instance my_chess_engine

Start    

    sudo docker start -a chess_engine_instance

Remove container

    sudo docker rm chess_engine_instance