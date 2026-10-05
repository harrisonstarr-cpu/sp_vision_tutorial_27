#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "nav_hw_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__nav_hw_interfaces__msg__SensorData() -> *const std::ffi::c_void;
}

#[link(name = "nav_hw_interfaces__rosidl_generator_c")]
extern "C" {
    fn nav_hw_interfaces__msg__SensorData__init(msg: *mut SensorData) -> bool;
    fn nav_hw_interfaces__msg__SensorData__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SensorData>, size: usize) -> bool;
    fn nav_hw_interfaces__msg__SensorData__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SensorData>);
    fn nav_hw_interfaces__msg__SensorData__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SensorData>, out_seq: *mut rosidl_runtime_rs::Sequence<SensorData>) -> bool;
}

// Corresponds to nav_hw_interfaces__msg__SensorData
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SensorData {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub seq: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub distance: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ranges: rosidl_runtime_rs::Sequence<f32>,

}



impl Default for SensorData {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !nav_hw_interfaces__msg__SensorData__init(&mut msg as *mut _) {
        panic!("Call to nav_hw_interfaces__msg__SensorData__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SensorData {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { nav_hw_interfaces__msg__SensorData__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { nav_hw_interfaces__msg__SensorData__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { nav_hw_interfaces__msg__SensorData__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SensorData {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SensorData where Self: Sized {
  const TYPE_NAME: &'static str = "nav_hw_interfaces/msg/SensorData";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__nav_hw_interfaces__msg__SensorData() }
  }
}


