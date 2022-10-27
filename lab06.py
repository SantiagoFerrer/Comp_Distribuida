#Julio Cesar- 32091524
#Lucas Andrew- 32092245
#Santiago Ferrer- 32035764

from flask import Flask
from flask import request
from flask import jsonify

import urllib.request, json

app = Flask(__name__)
app.config['JSON_SORT_KEYS'] = False

resultado = {
    "conversao":
        {
            "real": 0,
            "dolar": 0,
            "euro" : 0
        }
    }

@app.route('/convertemoeda/<int:valor>',methods=['GET'])
def ConversaoMoeda(valor):
    response = urllib.request.urlopen("https://economia.awesomeapi.com.br/json/last/BRL-USD,BRL-EUR")
    resp = response.read()
    resp_json = json.loads(resp)  
    real = valor
    dolar = resp_json["BRLUSD"]["high"]
    euro = resp_json["BRLEUR"]["high"]
    conv_dolar = round((float(dolar)*real),3)
    conv_euro = round((float(euro)*real),3)
    resultado["conversao"]["real"] = real
    resultado["conversao"]["dolar"] = conv_dolar
    resultado["conversao"]["euro"] = conv_euro

    return jsonify(resultado)

@app.route('/',methods=['GET'])
def home():
    return "SERVIDOR 2 ------------- Julio Cesar 32091524 / Lucas Andrew 32092245 / Santiago Ferrer 32035764"    

if __name__ == '__main__':
 app.run()
