'''
1.Train Model
2. Create Web APP using Flask and index.html for webui
3. Commit Code into Git
4. Create cloud account
5 Link Git to corresponding cloud
6. Build the model on clound in your account
7.run web application
8. share app with others

'''
import numpy as np
from flask import Flask,request,jsonify,render_template
import pickle

app = Flask(__name__)
model = pickle.load(open('model.pkl','rb'))
i=10
@app.route("/")
def home():
    return render_template("index.html")
@app.route("/predict", methods=["GET"])
def predict():
    print(request)
    print("iyyyyy = ",i)
    int_features = [int(x) for x in request.form.values()]
    final_features = [np.array(int_features)]
    prediction = model.predict(final_features)

    output = round(prediction[0],2)

    return render_template('index.html',prediction_text = "Employee Salary shoud be $ {}".format(output))

if __name__ == "__main__":
    app.run(debug=True)
print("End")
