"""
This file defines form control elements for the demo_module
See: https://docs.djangoproject.com/en/2.2/topics/forms/
And: https://simpleisbetterthancomplex.com/tutorial/2018/11/28/advanced-form-rendering-with-django-crispy-forms.html

Consider validation for the JSON
https://stackoverflow.com/questions/44085153/how-to-validate-a-json-object-in-django

"""

from django import forms

from crispy_forms.helper import FormHelper
from crispy_forms.layout import Layout, Submit, Row, Column

from .models import Status

class TestForm(forms.Form):
    #         "protocolVersion": {"type": "number"},
    #         "sentBy": {"type": "string"},
    #         "msgType": {"type": "string"},
    #         "commandList": {"type": "string"},
    #         "statusCode": {"type": "string"},
    #         "parameterObj": {"type": "object"},
    #         "dataObj": {"type": "object"},
    #         "embeddedFileFormat": {"type": "string"},
    #         "embeddedFile": {"type": "string"}

    PROTOCOL_VERSIONS = (
        ('1.0', 'Ver. 1.0'),
    )

    TOPICS = (
        ('demo_module/inbound', 'demo_module/inbound'),
        ('demo_module/outbound', 'demo_module/outbound'),
        ('test-stub-in', 'test-stub-in'),
        ('test-stub-out', 'test-stub-out'),
    )

    MSG_TYPES = (
        ('command', 'command'),
        ('data', 'data'),
        ('status', 'status'),
        ('result', 'result'),
    )

    SENSOR_TYPES = (
        ('1', 'adxl345'),
        ('2', 'Kx224'),
    )

    FREQ_LIST = (
        ('800', '800 Hz'),
    )

    STEPS = (
        ('1', '1'),
        ('2', '2'),
        ('5', '5'),
        ('10', '10'),
        ('20', '20'),
    )

    STEPTIMEMS = (
        ('1000', '1 sek'),
        ('2000', '2 sek'),
        ('3000', '3 sek'),
    )

    STEPSIZE = (
        ('5', '5 Hz'),
        ('10', '10 Hz'),
        ('20', '20 Hz'),
        ('50', '50 Hz'),
        ('100', '100 Hz'),
    )

    sensorID = forms.ChoiceField(
        label='Sensortype',
        choices=SENSOR_TYPES
    )

    steps = forms.ChoiceField(
        label='Steps',
        choices=STEPS
    )

    stepTimems = forms.ChoiceField(
        label='Steptime',
        choices=STEPTIMEMS
    )

    stepSize = forms.ChoiceField(
        label='Step [Hz]',
        choices=STEPSIZE
    )

    sampleFrequency = forms.ChoiceField(
        label='Samplingfrekvens [Hz]',
        choices=FREQ_LIST
    )

    #
    protocol_version = forms.ChoiceField(
        label='Protokol',
        choices=PROTOCOL_VERSIONS
    )

    # mqtt message form
    topic = forms.ChoiceField(
        label='Emne (mqtt)',
        choices=TOPICS,
    )

    msg_type = forms.ChoiceField(
        label='Beskedtype',
        choices=MSG_TYPES
    )

    status_code = forms.ChoiceField(
        label='Statuskode',
        choices=Status.STATUS_CODES
    )

    command_list_str = forms.CharField(
        label='Kommandoer (JSON-streng med liste af key-value pairs)',
        widget=forms.TextInput(attrs={
            'value': '["cmd1", "cmd2"]',
            'placeholder': '["cmd1", "cmd2"]'
        }),
        required=False
    )

    parameter_obj_str = forms.CharField(
        label='Parametre (JSON-streng med liste af key-value pairs)',
        widget=forms.Textarea(attrs={
            'placeholder': '{"param1": "val1", "param2": "val2"}'
        }),
        initial='{"param1": "val1", "param2": "val2"}',
        required=False
    )

    data_obj_str = forms.CharField(
        label='Dataobjekt (JSON-streng med liste af key-value pairs)',
        widget=forms.Textarea(attrs={
            'placeholder': '{ "x": [1,2,3,4,5,6,7,8,9,10], "y": [1,4,9,16,25,36,49,64,81,100] }'
        }),
        initial='{ "x": [1,2,3,4,5,6,7,8,9,10], "y": [1,4,9,16,25,36,49,64,81,100] }',
        required=False
    )

    # Who requested this data
    sender = forms.CharField(
        label='Opretter (navn)',
        required=True,
        widget=forms.TextInput(attrs={
            'value': 'testbruger'
        })
    )

    # tag data to keep it in the db forever
    no_delete = forms.BooleanField(
        label='Gem data permanent',
        required=False
    )

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.helper = FormHelper()
        self.helper.layout = Layout(

            Row(
                Column('sensorID', css_class='form-group col-md-4 mb-0'),
                css_class='form-row'
            ),
            Row(
                Column('sampleFrequency', css_class='form-group col-md-4 mb-0'),
                css_class='form-row'
            ),
            Row(
                Column('steps', css_class='form-group col-md-4 mb-0'),
                Column('stepTimems', css_class='form-group col-md-4 mb-0'),
                Column('stepSize', css_class='form-group col-md-4 mb-0'),
                css_class='form-row'
            ),
            'sender',
            'no_delete',
            Submit('submit', 'Start test')
        )



class AccelerometerForm(forms.Form):
    """
    Denne klasse implementerer formularen til GUI-demo, som vises på Webinterface
    """
    SENSOR_TYPES = (
        ('adxl345', 'adxl345'),
        ('Kx224', 'Kx224'),
    )

    FREQ_LIST = (
        ('10', '10 Hz'),
        ('100', '100 Hz'),
        ('1000', '1 kHz'),
        ('10000', '10 kHz'),
    )

    sensor_type = forms.ChoiceField(
        label='Sensortype',
        choices=SENSOR_TYPES
    )

    duration = forms.CharField(
        label='Varighed af test (sekunder)',
        widget=forms.TextInput(attrs={
            'value': '10',
            'placeholder': 'Indtast antal sekunder her'
        }),
        required=True
    )

    step = forms.CharField(
        label='Steps',
        widget=forms.TextInput(attrs={
            'placeholder': 'Indtast steps her'
        }),
        required=True
    )

    stepTime = forms.CharField(
        label='Steptime i [ms]',
        widget=forms.TextInput(attrs={
            'value': '10',
            'placeholder': 'Indtast stepTime her'
        }),
        required=True
    )

    stepSize = forms.CharField(
        label='Steptime [int]',
        widget=forms.TextInput(attrs={
            'value': '10',
            'placeholder': 'Indtast stepSize her'
        }),
        required=True
    )

    freq = forms.ChoiceField(
        label='Frekvens [Hz]',
        choices=FREQ_LIST
    )


    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.helper = FormHelper()
        self.helper.layout = Layout(
            'sensor_type',
            'duration',
            'step',
            'stepTime',
            'stepSize',
            'freq',
            Submit('submit', 'En knap :)')
        )