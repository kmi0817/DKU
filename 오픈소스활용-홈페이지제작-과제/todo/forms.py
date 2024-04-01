from django.forms import ModelForm
from .models import Homework

class homeworkForm(ModelForm) :
    class Meta :
        model = Homework
        fields = '__all__'