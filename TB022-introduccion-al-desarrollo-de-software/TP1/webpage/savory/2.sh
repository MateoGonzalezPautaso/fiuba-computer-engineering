#!/bin/bash
# dependencias api y frontend
pipenv install requests

pipenv install mysql-connector-python
pipenv install SQLAlchemy
pipenv install Flask-SQLAlchemy

# iniciar base de datos
cd database || exit
cd docker || exit
sudo chmod 666 /var/run/docker.sock
docker compose up --build -d