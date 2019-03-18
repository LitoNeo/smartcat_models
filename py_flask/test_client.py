# -*- coding:utf-8 -*-

from flask import Flask, render_template
from flask_socketio import SocketIO, emit

app = Flask(__name__)
app.config["SECRET_KEY"] = "secret!"
socketio = SocketIO(app)


@app.route('/')
def hello():
    return "welcome"


@app.route('/index')
def index():
    return "Here"


@socketio.on('connect', namespace='/test')
def test_connect():
    emit('my response', {'data': 'success'})


@socketio.on('disconnect', namespace='/test')
def test_disconnect():
    print("shut down")


if __name__ == "__main__":
    socketio.run(app, host="127.0.0.1", port=6666, debug=True)