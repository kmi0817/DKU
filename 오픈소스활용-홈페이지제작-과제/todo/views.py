from django.db.models.query import QuerySet
from django.shortcuts import get_object_or_404, render, redirect
from django.urls import reverse
from django.db.models import Q
from django.contrib import messages

from .models import *
from .forms import homeworkForm
from .filters import *

def index(request) :
    course_list = Course.objects.all()
    hw_list = Homework.objects.all()

    cFilter = CourseFilter(request.GET, queryset=course_list)
    course_list = cFilter.qs

    context = {
        'course_list' : course_list,
        'hw_list' : hw_list,
        'cFilter' : cFilter,
        }
    return render(request, 'todo/index.html', context)

def detail(request, homework_id) :
    hw = get_object_or_404(Homework, pk=homework_id)
    context = {'hw' : hw}
    return render(request, 'todo/detail.html', context)

def createForm(request) :
    form = homeworkForm()

    if request.method == 'POST' :
        form = homeworkForm(request.POST)
        if form.is_valid() :
            form.save()
            return redirect(reverse('todo:index'))
    
    context = {'form' : form}
    return render(request, 'todo/form.html', context)

def updateForm(request, homework_id) :
    homework = get_object_or_404(Homework, pk=homework_id)
    form = homeworkForm(instance=homework)

    if request.method == 'POST' :
        form = homeworkForm(request.POST, instance=homework)
        if form.is_valid() :
            form.save()
            return redirect(reverse('todo:index'))

    context = {'form' : form}
    return render(request, 'todo/form.html', context)

def deleteForm(homework_id) :
    homework = get_object_or_404(Homework, pk=homework_id)
    homework.delete()
    return redirect(reverse('todo:index'))