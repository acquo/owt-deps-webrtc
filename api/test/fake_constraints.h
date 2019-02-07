/*
 *  Copyright 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef API_TEST_FAKE_CONSTRAINTS_H_
#define API_TEST_FAKE_CONSTRAINTS_H_

#include <string>
#include <vector>

#include "api/media_constraints_interface.h"
#include "rtc_base/string_encode.h"

namespace webrtc {

class FakeConstraints : public webrtc::MediaConstraintsInterface {
 public:
  FakeConstraints() {}
  virtual ~FakeConstraints() {}

  virtual const Constraints& GetMandatory() const { return mandatory_; }

  virtual const Constraints& GetOptional() const { return optional_; }

  template <class T>
  void AddMandatory(const std::string& key, const T& value) {
    mandatory_.push_back(Constraint(key, rtc::ToString(value)));
  }

  template <class T>
  void SetMandatory(const std::string& key, const T& value) {
    std::string value_str;
    if (mandatory_.FindFirst(key, &value_str)) {
      for (Constraints::iterator iter = mandatory_.begin();
           iter != mandatory_.end(); ++iter) {
        if (iter->key == key) {
          mandatory_.erase(iter);
          break;
        }
      }
    }
    mandatory_.push_back(Constraint(key, rtc::ToString(value)));
  }

  template <class T>
  void AddOptional(const std::string& key, const T& value) {
    optional_.push_back(Constraint(key, rtc::ToString(value)));
  }

  void SetMandatoryReceiveAudio(bool enable) {
    SetMandatory(MediaConstraintsInterface::kOfferToReceiveAudio, enable);
  }

  void SetMandatoryReceiveVideo(bool enable) {
    SetMandatory(MediaConstraintsInterface::kOfferToReceiveVideo, enable);
  }

  void SetMandatoryUseRtpMux(bool enable) {
    SetMandatory(MediaConstraintsInterface::kUseRtpMux, enable);
  }

  void SetMandatoryIceRestart(bool enable) {
    SetMandatory(MediaConstraintsInterface::kIceRestart, enable);
  }

  void SetAllowRtpDataChannels() {
    SetMandatory(MediaConstraintsInterface::kEnableRtpDataChannels, true);
    SetMandatory(MediaConstraintsInterface::kEnableDtlsSrtp, false);
  }

  void SetOptionalVAD(bool enable) {
    AddOptional(MediaConstraintsInterface::kVoiceActivityDetection, enable);
  }

  void SetAllowDtlsSctpDataChannels() {
    SetMandatory(MediaConstraintsInterface::kEnableDtlsSrtp, true);
  }

 private:
  Constraints mandatory_;
  Constraints optional_;
};

}  // namespace webrtc

#endif  // API_TEST_FAKE_CONSTRAINTS_H_
