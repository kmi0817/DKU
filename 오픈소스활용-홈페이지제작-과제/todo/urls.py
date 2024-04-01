from django.urls import path
from . import views

app_name = 'todo'
urlpatterns = [
    path('', views.index, name='index'),
    path('<int:homework_id>/', views.detail, name='detail'),
    path('createForm/', views.createForm, name='createForm'),
    path('updateFrom/<int:homework_id>/', views.updateForm, name='updateForm'),
    path('deleteForm/<int:homework_id>/', views.deleteForm, name='deleteForm'),
]