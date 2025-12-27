#!/bin/bash

mkdir ParcialIDS
cd ParcialIDS

touch app.py
mkdir .venv

pipenv install flask

mkdir templates
mkdir static
cd static
mkdir images
mkdir css
cd ..
ls

