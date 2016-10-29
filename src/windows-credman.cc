#include <nan.h>
#include <wincred.h>



using namespace v8;



NAN_METHOD(GetCredentials) {  
  auto isolate = info.GetIsolate();

  if (info.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You should provide saved credentials name")));
    return;
  }

  if (!info[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "First parameter is not a string")));
    return;
  }

  auto targetNameValue = info[0]->ToString();
  auto length = targetNameValue->Length();
  auto buffer = new TCHAR[length];

  #ifdef UNICODE
    targetNameValue->Write((uint16_t *)buffer);
  #else
    targetNameValue->WriteOneByte((uint8_t *)buffer);
  #endif

  PCREDENTIAL cred;
  if(::CredRead(buffer, CRED_TYPE_GENERIC, 0, &cred))
  {
    auto blobSize = cred->CredentialBlobSize;
    auto password = String::NewFromTwoByte(isolate, (uint16_t *)cred->CredentialBlob, NewStringType::kNormal, blobSize/2);
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    Nan::Set(obj, Nan::New("username").ToLocalChecked(), Nan::New(cred->UserName).ToLocalChecked());
    Nan::Set(obj, Nan::New("password").ToLocalChecked(), password.ToLocalChecked());

    info.GetReturnValue().Set(obj);

    ::CredFree(cred);
  }

  delete[] buffer;
}

NAN_MODULE_INIT(InitAll) {

  Nan::Set(target, Nan::New<String>("getCredentials").ToLocalChecked(),

    Nan::GetFunction(Nan::New<FunctionTemplate>(GetCredentials)).ToLocalChecked());
}


NODE_MODULE(addon, InitAll)