
module.exports =  function(env){
    if(env == 'production'){
        return "postgres://postgres:M3ss3ng3rS3rvic3@localhost:5432/pinventory"
    }else if(env == 'development') {
        return "postgres://postgres:M3ss3ng3rS3rvic3@localhost:5432/pinventory_dev"
    }else if(env == 'local'){
        return "postgres://postgres:M3ss3ng3rS3rvic3@localhost:5432/pinventory_dev"
    }
}

