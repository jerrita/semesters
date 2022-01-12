from model import Display, Storage, Controller
import picoweb
import ulogging as logging
import ujson as json
from dfmini import Player

# Storage init
s = Storage('data.db')
d = Display()
# s.update('ssid', 'Redrock')
# s.update('password', 'RedrockStaff@2020')
s.update('ssid', 'Noir')
s.update('password', 'pa5sw0rd')
c = Controller(s)

# Wifi init
d.show_connecting_screen()
status = c.connect()

if not status:
    d.show_fallback()
else:
    d.show_wifi_detail(s.get('ssid'), s.get('ip'))

# Router init
app = picoweb.WebApp(__name__)

# Player init
p = Player()
p.volume(10)


def update_volume(v=0):
    res = p.volume(v)
    d.show_play_detail(s.get('ssid'), s.get('ip'), res)
    return res


@app.route("/")
def index(req, resp):
    yield from picoweb.start_response(resp)
    yield from resp.awrite("Hello Music Center!")


@app.route('/api/volume')
def volume_op(req, resp):
    if req.method == "POST":
        yield from req.read_form_data()
    else:
        req.parse_qs()

    print(req.form)
    yield from picoweb.start_response(resp)
    if 'volume' not in req.form:
        yield from resp.awrite(json.dumps({
            'code': 1,
            'volume': update_volume(),
            'msg': 'Request error'
        }))
    else:
        volume = int(req.form['volume'])
        res = update_volume(volume)
        yield from resp.awrite(json.dumps({
            'code': 0,
            'volume': res,
            'msg': 'Success'
        }))


@app.route('/api/play')
def play_op(req, resp):
    if req.method == "POST":
        yield from req.read_form_data()
    else:
        req.parse_qs()

    update_volume()
    yield from picoweb.start_response(resp)
    if 'method' not in req.form:
        yield from resp.awrite(json.dumps({
            'code': 1,
            'msg': 'Request error'
        }))
    else:
        method = req.form['method']
        if method == 'pause':
            p.pause()
        elif method == 'next':
            p.play(track_id='next')
        elif method == 'pre':
            p.play(track_id='prev')
        elif method == 'select':
            if 'id' not in req.form:
                yield from resp.awrite(json.dumps({
                    'code': 1,
                    'msg': 'Select method needs a song id!'
                }))
                return
            else:
                song_id = int(req.form['id'])
                p.play(song_id)
        else:
            method = 'play'
            p.play()
        yield from resp.awrite(json.dumps({
            'code': 0,
            'method': method,
            'msg': 'send'
        }))


logging.basicConfig(level=logging.INFO)

# Application start
# def run():
#     app.run(debug=True, host='0.0.0.0', port=80)

app.run(debug=True, host='0.0.0.0', port=80)
