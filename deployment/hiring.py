# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

#!pip install flask-ngrok
from flask_ngrok import run_with_ngrok
from flask import Flask
app = Flask(__name__)
run_with_ngrok(app)   #starts ngrok when the app is run
@app.route("/")
def home():
    return "<h1>Running Flask on Google Colab ccxxxxxxx!</h1>"
  
app.run()