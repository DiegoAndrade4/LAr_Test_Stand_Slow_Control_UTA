from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import smtplib
import yaml



def meta_loader():
    # Load the data from config.yml file 
    """Utility function to load email parameters."""

    with open('config.yml') as config:
        meta = yaml.load(config, Loader=yaml.FullLoader)

    return meta


def send_email(meta):
    """Utility function to send email to users from meta."""

    # Setup email configurations
    message = MIMEMultipart('alternative')
    message['Subject'] = meta['subject']
    message['From'] = meta['email']
    message['To'] = ", ".join(meta['recipients'])

    # Build email body
    html = "<h1>The oxygen level is low.<h1>"
    body = MIMEText(html, 'html')
    message.attach(body)

    # Create secure connection with server and send email
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login(meta['email'], meta['password'])
    text = message.as_string()
    server.sendmail(meta['email'], meta['recipients'], text)
    server.quit()


def Notify():
    """Utility function to notify the low oxygen level."""

    # Load email meta data
    meta = meta_loader()
    send_email(meta)

                


