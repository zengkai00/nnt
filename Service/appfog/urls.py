from django.conf.urls.defaults import *
from django.views.generic.simple import direct_to_template
from django.contrib import admin

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
                           
    # wsi sites.
    url(r'^api$', 'wsi.api.main.dispatch'),
    url(r'^pub/', include('wsi.sites.pub')),

    # Uncomment the admin/doc line below to enable admin documentation:
    url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    url(r'^admin/', include(admin.site.urls)),
    
    # for unhandle url.
    # url(r'^.*$', direct_to_template, {'template': 'null.html'}),
)