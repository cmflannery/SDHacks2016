package com.docusign.esign.model;

import java.util.Objects;
import com.docusign.esign.model.TabMetadata;
import com.fasterxml.jackson.annotation.JsonProperty;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;





@javax.annotation.Generated(value = "class io.swagger.codegen.languages.JavaClientCodegen", date = "2016-07-18T18:11:15.675-07:00")
public class TabMetadataList   {
  
  private java.util.List<TabMetadata> tabs = new java.util.ArrayList<TabMetadata>();

  
  /**
   * 
   **/
  public TabMetadataList tabs(java.util.List<TabMetadata> tabs) {
    this.tabs = tabs;
    return this;
  }
  
  @ApiModelProperty(example = "null", value = "")
  @JsonProperty("tabs")
  public java.util.List<TabMetadata> getTabs() {
    return tabs;
  }
  public void setTabs(java.util.List<TabMetadata> tabs) {
    this.tabs = tabs;
  }

  

  @Override
  public boolean equals(java.lang.Object o) {
    if (this == o) {
      return true;
    }
    if (o == null || getClass() != o.getClass()) {
      return false;
    }
    TabMetadataList tabMetadataList = (TabMetadataList) o;
    return Objects.equals(this.tabs, tabMetadataList.tabs);
  }

  @Override
  public int hashCode() {
    return Objects.hash(tabs);
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("class TabMetadataList {\n");
    
    sb.append("    tabs: ").append(toIndentedString(tabs)).append("\n");
    sb.append("}");
    return sb.toString();
  }

  /**
   * Convert the given object to string with each line indented by 4 spaces
   * (except the first line).
   */
  private String toIndentedString(java.lang.Object o) {
    if (o == null) {
      return "null";
    }
    return o.toString().replace("\n", "\n    ");
  }
}

