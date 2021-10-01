const express = require('express')
const cookieParser = require('cookie-parser')
const app = express()
const port = process.env.PORT || 4200

//Google Auth
const {OAuth2Client} = require('google-auth-library');
const CLIENT_ID = '180374672702-vad12pe1q4og9dr4mjra0hrsj57ol1im.apps.googleusercontent.com'
const client = new OAuth2Client(CLIENT_ID);

//Middleware
app.set('view engine', 'ejs')
app.use(express.json());
app.use(cookieParser());

app.get('/', (req, res)=>{
    res.render('index')
})

app.get('/login', (req, res)=>{
    res.render('login')
})

// login
app.post('/login', (req, res)=>{
    let token = req.body.token;

    async function verify() {
        const ticket = await client.verifyIdToken({
            idToken: token,
            audience: CLIENT_ID,
        });
        const payload = ticket.getPayload();
        const userid = payload['sub'];
        console.log(payload)
    }
    verify()
        .then(()=>{
            res.cookie('session-token', token);
            res.send('success');
        }).
    catch(console.error);
})

app.get('/dashboard', checkAuthenticated, (req, res)=>{
    let user = req.user;
    res.render('dashboard', {user});
    console.log(user.email)
})

app.get('/protectedroute', checkAuthenticated, (req,res)=>{
    res.render('protectedroute');
})

app.get('/logout', (req, res) => {
    res.clearCookie('session-token');
    res.redirect('/login')
})

app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`)
})

function checkAuthenticated(req, res, next){

    let token = req.cookies['session-token'];

    let user = {};
    async function verify(){
        const ticket = await client.verifyIdToken({
            idToken: token,
            audience: CLIENT_ID,
        });
        const payload = ticket.getPayload();
        user.name = payload.name;
        user.email = payload.email;
        user.picture = payload.picture;
    }
    verify()
        .then(() =>{
            req.user = user;
            next();
        })
        .catch(err=>{
            res.redirect('/login')
        })
}