from django.db import models

class Course(models.Model) :
    course_name = models.CharField(max_length=100)
    create_date = models.DateTimeField('create published')

    def __str__(self) :
        return self.course_name
    
class Homework(models.Model) :
    cname = models.ForeignKey(Course, on_delete=models.CASCADE)
    title = models.CharField(max_length=200) # 과제 이름
    desc = models.CharField(max_length=500, null=True) # 과제 설명
    done = models.BooleanField(default=False) # 과제 완성 여부

    def __str__(self) :
        return self.title
