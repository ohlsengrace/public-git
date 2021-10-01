
module.exports =  function(env){
    if(env == 'production'){
        return "postgres://pinventory" //incorrect but not shown for security reasons
    }else if(env == 'development') {
        return "postgres://pinventory_dev" //incorrect but not shown for security reasons
    }else if(env == 'local'){
        return "postgres://pinventory_dev" //incorrect but not shown for security reasons
    }
}

