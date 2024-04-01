from django.contrib import admin

from .models import Course, Homework

admin.site.register(Course)
admin.site.register(Homework)