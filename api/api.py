#docker API

from flask import Flask, request, jsonify
from flask_restful import Resource, Api
from copy import deepcopy
import sys
import socket

'''
Simple API to send input to botnet dispatcher
'''

#Define dispatcher constants
HOST = "127.0.0.1" #TODO change to real IP
PORT = 25000

#Connect to dispatcher
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
while(True):
    try:
        sock.connect((HOST, PORT))
    except:
        continue


app = Flask(__name__)
api = Api(app)

def exit_critical():
    sys.exit("Critical error has occured, exiting...")

def get_num():
    num_str = request.args.get("number")
    return num_str

def send_num(num_str):
   sock.sendall(num_str)

# -1 = bad number, 0 = good number
def check_num(num_str);
    try:
        num_int = int(num_str)
    except:
        return -1

    if num_int >= 0 and num_int <= 65535:
        return 0
    else:
        return -1

class Botnet_RESTAPI(Resource):
    #On receive
    def on_post(self):
        num = get_num()
        #If number is garbage
        if check_num(num_str) == -1:
            pass
        #Else if number is good
        else:
            send_num(num)

#Start API on port 5000
api.add_resource(Botnet_RESTAPI, '/')
if __name__ == "__main__":
    app.run(host="0.0.0.0", port="5000", debug=True)
