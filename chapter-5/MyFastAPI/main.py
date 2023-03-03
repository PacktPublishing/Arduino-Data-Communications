from typing import Union

from fastapi import FastAPI

app = FastAPI()


@app.get("/")
def read_root():
    return {"App": "MySQL API using FastAPI"}


@app.get("/stations")
def read_stations():
    return {"stations": []}