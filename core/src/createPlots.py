import plotly
plotly.tools.set_credentials_file(username='tutorial.account', api_key='gxa2ckhtj2')
import plotly.plotly as py
import plotly.graph_objs as go
import json

file_content = ""
with open('/Users/Baratta/Downloads/nbodyblackmagic-export.json') as file_s:
    lines = file_s.readlines()
    file_content = "\n".join(lines)
    
frame = json.loads(file_content)

# Timestep that we're using in days
timestep = frame["timestep"]
frameList = frame["frames"]

data = []
numberOfBodies = len(frameList[0]["frame"])

for i in range(numberOfBodies):
    (x, y) = ([], [])
    for frame in frameList:
        body = frame["frame"][i]
        x.append(body["pos"]["x"])
        y.append(body["pos"]["y"])
    
    trace = go.Scatter(
            x = x,
            y = y,
            mode = 'lines+markers',
            name = 'lines+markers'
            )
    
    data.append(trace)
    
    layout = go.Layout(
    title='Position vs. Time ',
    yaxis=dict(
        title='Position (Au)'
    ),
    xaxis=dict(
        title='Time (days)',
        titlefont=dict(
            color='rgb(148, 103, 189)'
        ),
        tickfont=dict(
            color='rgb(148, 103, 189)'
        ),
        overlaying='y',
        side='right'
    )
)
fig = go.Figure(data=data, layout=layout)
py.iplot(fig, filename='scatter-mode', fileopt='extend')
data = []
numberOfBodies = len(frameList[0]["frame"])

for i in range(numberOfBodies):
    (t, k) = ([], [])
    for frameNumber, frame in enumerate(frameList):
        body = frame["frame"][1]
        k.append(body["kinetic"])
        t.append(frameNumber * timestep)
        
    trace = go.Scatter(
            x = t,
            y = k,
            mode = 'lines+markers',
            name = 'lines+markers'
            )
    
    data.append(trace)
    
    layout = go.Layout(
    title='Kinetic Energy vs. Time ',
    yaxis=dict(
        title='Kinetic Energy x (1.79X10^37) J'
    ),
    xaxis=dict(
        title='Time (days)',
        titlefont=dict(
            color='rgb(148, 103, 189)'
        ),
        tickfont=dict(
            color='rgb(148, 103, 189)'
        ),
        overlaying='y',
        side='right'
    )
)

    fig = go.Figure(data=data, layout=layout)
py.iplot(fig, filename='scatter-mode2', fileopt='extend')
data = []
numberOfBodies = len(frameList[0]["frame"])

for i in range(numberOfBodies):
    (t, k) = ([], [])
    for frameNumber, frame in enumerate(frameList):
        body = frame["frame"][1]
        k.append(body["potential"])
        t.append(frameNumber * timestep)
        
    trace = go.Scatter(
            x = t,
            y = k,
            mode = 'lines+markers',
            name = 'lines+markers'
            )
            
    
    data.append(trace)
    
    layout = go.Layout(
    title='Potential Energy vs. Time ',
    yaxis=dict(
        title='Potential Energy x (1.79x10^37) J'
    ),
    xaxis=dict(
        title='Time (days)',
        titlefont=dict(
            color='rgb(148, 103, 189)'
        ),
        tickfont=dict(
            color='rgb(148, 103, 189)'
        ),
        overlaying='y',
        side='right'
    )
)
fig = go.Figure(data=data, layout=layout)
py.iplot(fig, filename='scatter-mode55', fileopt='extend')


file_content = ""
with open('/Users/Baratta/Downloads/nbodyblackmagic-export.json') as file_s:
    lines = file_s.readlines()
    file_content = "\n".join(lines)
    
frame = json.loads(file_content)

# Timestep that we're using in days
timestep = frame["timestep"]
frameList = frame["frames"]


data = []
numberOfBodies = len(frameList[0]["frame"])

for i in range(numberOfBodies):
    (t, k, u, s) = ([], [], [], [])
    for frameNumber, frame in enumerate(frameList):
        body = frame["frame"][1]
        k.append(body['kinetic'])
        u.append(body['potential'])
        t.append(frameNumber * timestep)
        
        s.append(body['kinetic'] + body['potential'])
            
    data.append(go.Scatter(
            x = t,
            y = k,
            mode = 'lines+markers',
            name = 'lines+markers'
            ))
    
    data.append(go.Scatter(
            x = t,
            y = u,
            mode = 'lines+markers',
            name = 'lines+markers'
            ))
            
    data.append(go.Scatter(
            x = t,
            y = s,
            mode = 'lines+markers',
            name = 'lines+markers'
            ))
    
    layout = go.Layout(
    title='Mechanical Energy vs. Time ',
    yaxis=dict(
        title='Mechanical Energy x (1.79x10^31) J'
    ),
    xaxis=dict(
        title='Time (days)',
        titlefont=dict(
            color='rgb(148, 103, 189)'
        ),
        tickfont=dict(
            color='rgb(148, 103, 189)'
        ),
        overlaying='y',
        side='right'
    )
)
fig = go.Figure(data=data, layout=layout)
py.iplot(data, filename='COMBINED', fileopt='extend')
