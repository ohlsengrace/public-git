
const db = require('./connection.js');


// clears student database and updates it with current list in powerschool

function updateStudents(obj){

    db.none('DELETE FROM students')
        .then(() => {
            console.log('students table successfully cleared');
        })
        .catch(error => {
            console.log(error)
        })

    for(i = 0; i < obj.items.length; i++){
        schoolId = obj.items[i].schoolid;
        studentNumber = obj.items[i].student_number;
        firstName = obj.items[i].first_name;
        lastName = obj.items[i].last_name;
        gradeLevel = obj.items[i].grade_level;

            db.none('INSERT INTO students VALUES($1,$2,$3,$4,$5)', [schoolId,studentNumber,firstName,lastName,gradeLevel])
                .then( () => {
                })
                .catch(error => {
                    console.log(error)
                })
        }
        console.log('updateStudents completed')
    }

    // updates all student emails
    function updateEmails(obj){

        for(i=0; i < obj.length; i++) {
            studentNumber = obj[i].student_number.toString();
            email = obj[i]['email'];

            db.none('UPDATE students SET email = $1 WHERE student_number = $2', [email, studentNumber])
                .then(() => {
                })
                .catch(error => {
                    console.log(error)
                })
        }
         console.log('updateEmails completed')
        }



module.exports = {
    updateStudents, updateEmails
}
